#include "wxEmailMessage.h"
#include "wxEmailMessageID.h"
#include <wx/datetime.h>

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

/*
  "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
  "To: " TO "\r\n",
  "From: " FROM "(Example User)\r\n",
  "Cc: " CC "(Another example User)\r\n",
  "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@rfcpedant.example.org>\r\n",
  "Subject: SMTP TLS example message\r\n",
  "\r\n",
  "The body of the message starts here.\r\n",
  "\r\n",
  "It could be a lot of lines, could be MIME encoded, whatever.\r\n",
  "Check RFC5322.\r\n",
  NULL
};

*/

wxString wxEmailMessage::PayLoad() const
{
    wxString payload;
    payload << "Date: " << wxDateTime::Now().Format() << "\r\n";
    payload << "To: " << GetTo() << "\r\n";
    payload << "From: " << GetFrom() << "\r\n";
    payload << "Cc: \r\n";
    payload << "Message-ID: " << GenerateID() << "\r\n";
    payload << "Subject: " << GetSubject() << "\r\n";
    payload << "\r\n";
    payload << GetMessage() << "\r\n";
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
