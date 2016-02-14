#include "wxEmailMessage.h"
#include "wxEmailMessageID.h"
#include <wx/datetime.h>
#include <wx/ffile.h>
#include <wx/base64.h>
#include <wx/msgdlg.h>

#define BOUNDRY_LINE "pj+EhsWuSQJxx7pr"

wxEmailMessage::wxEmailMessage()
    : m_aschar(NULL)
    , m_pos(0)
    , m_len(0)
{
}

wxEmailMessage::~wxEmailMessage()
{
    if(m_aschar) {
        free(m_aschar);
    }
    m_aschar = NULL;
}

wxString wxEmailMessage::GenerateID()
{
    static time_t starupTime = time(NULL);
    time_t curtime = time(NULL);

    wxString s;
    s << starupTime << "." << curtime;
    wxEmailMessageID id(s);
    s = id.Encrypt();

    s.Prepend("<");
    s << "@wxmailer>";
    return s;
}

wxString wxEmailMessage::PayLoad() const
{
    wxString payload;
    payload << "Date: " << wxDateTime::Now().Format() << "\r\n";
    payload << "To: " << GetTo() << "\r\n";
    payload << "From: " << GetFrom() << "\r\n";
    payload << "Cc: \r\n";
    payload << "Message-ID: " << GenerateID() << "\r\n";
    payload << "Subject: " << GetSubject() << "\r\n";

    bool hasAttachement = false;
    wxString base64Attachment;
    // Read the file and convert to base64
    if(GetAttachement().IsOk() && GetAttachement().Exists()) {
        FILE* fp = fopen(GetAttachement().GetFullPath().mb_str(wxConvUTF8).data(), "rb");
        if(fp) {
            fseek(fp, 0, SEEK_END);
            size_t len = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            hasAttachement = true;

            char* buffer = new char[len];
            fread(buffer, 1, len, fp);
            fclose(fp);
            base64Attachment = ::wxBase64Encode(buffer, len);
            wxDELETEA(buffer);
        }
    }

    // Sending attachment
    payload << "Content-Type: multipart/mixed; boundary=\"" << BOUNDRY_LINE << "\"\r\n";
    payload << "Mime-version: 1.0\r\n";
    payload << "\r\n";
    payload << "This is a multi-part message in MIME format. \r\n";

    // Message body
    if(!GetMessage().IsEmpty()) {
        payload << "\r\n--" << BOUNDRY_LINE << "\r\n";
        payload << "Content-Type: text/plain; charset=\"us-ascii\"\r\n";
        payload << "Content-Transfer-Encoding: quoted-printable \r\n";
        payload << "\r\n";
        payload << GetMessage() << "\r\n";
    }

    if(hasAttachement) {
        payload << "\r\n--" << BOUNDRY_LINE << "\r\n";
        payload << "Content-Type: application/octet-stream; name=\"" << GetAttachement().GetFullName() << "\""
                << "\r\n";
        payload << "Content-Transfer-Encoding: base64 \r\n";
        payload << "Content-Disposition: attachement; filename=\"" << GetAttachement().GetFullName() << "\"\r\n";
        payload << "\r\n";
        // Split the content to 76 chars per line
        while(!base64Attachment.IsEmpty()) {
            size_t bytes = (base64Attachment.length() >= 76) ? 76 : base64Attachment.length();
            wxString line = base64Attachment.Mid(0, bytes);
            payload << line << "\r\n";
            base64Attachment = base64Attachment.Mid(bytes);
        }
    }
    payload << "\r\n";
    return payload;
}

void wxEmailMessage::Finalize()
{
    m_payload = PayLoad();
    const char* p = m_payload.mb_str(wxConvUTF8).data();
    m_aschar = (char*)malloc(strlen(p) + 1);
    strcpy(m_aschar, p);
    m_len = strlen(m_aschar);
    m_pos = 0;
}
