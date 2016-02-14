#ifndef WXEMAILMESSAGE_H
#define WXEMAILMESSAGE_H

#include <wx/string.h>
#include <wx/filename.h>

class wxEmailMessage
{
    wxString m_from;
    wxString m_to;
    wxString m_subject;
    wxString m_message;
    wxString m_payload;
    wxFileName m_attachement;

    char* m_aschar;
    size_t m_pos;
    size_t m_len;

public:
    wxEmailMessage();
    virtual ~wxEmailMessage();

    /**
     * @brief finalize the message and prepare it for send
     */
    void Finalize();

    char* AsChar() const { return m_aschar + m_pos; }
    size_t Len() const { return m_len; }
    void Consume(size_t bytes) { m_pos += bytes; }
    bool HasMore() const { return (m_len > m_pos); }

    /**
     * @brief generate a unique message ID
     */
    static wxString GenerateID();

    /**
     * @brief Create the message payload
     */
    wxString PayLoad() const;

    wxEmailMessage& SetAttachement(const wxFileName& attachement)
    {
        this->m_attachement = attachement;
        return *this;
    }
    const wxFileName& GetAttachement() const { return m_attachement; }
    wxEmailMessage& SetFrom(const wxString& from)
    {
        this->m_from = from;
        return *this;
    }
    wxEmailMessage& SetMessage(const wxString& message)
    {
        this->m_message = message;
        return *this;
    }
    wxEmailMessage& SetSubject(const wxString& subject)
    {
        this->m_subject = subject;
        return *this;
    }
    wxEmailMessage& SetTo(const wxString& to)
    {
        this->m_to = to;
        return *this;
    }
    const wxString& GetFrom() const { return m_from; }
    const wxString& GetMessage() const { return m_message; }
    const wxString& GetSubject() const { return m_subject; }
    const wxString& GetTo() const { return m_to; }
};

#endif // WXEMAILMESSAGE_H
