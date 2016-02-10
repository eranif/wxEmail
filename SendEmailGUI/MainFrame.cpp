#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include "wxMailer.h"
#include <wx/msgdlg.h>

MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
}

MainFrame::~MainFrame() {}

void MainFrame::OnExit(wxCommandEvent& event)
{
    wxUnusedVar(event);
    Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxUnusedVar(event);
    wxAboutDialogInfo info;
    info.SetCopyright(_("My MainFrame"));
    info.SetLicence(_("GPL v2 or later"));
    info.SetDescription(_("Short description goes here"));
    ::wxAboutBox(info);
}
void MainFrame::OnSend(wxCommandEvent& event)
{
    wxMailer mailer(GetTextCtrlGmail()->GetValue(), GetTextCtrlPassword()->GetValue(), GetTextCtrlSmtp()->GetValue());
    wxEmailMessage message;
    message.SetFrom(GetTextCtrlFrom()->GetValue())
        .SetTo(GetTextCtrlTo()->GetValue())
        .SetMessage(GetTextCtrlBody()->GetValue())
        .SetSubject(GetTextCtrlSubject()->GetValue());

    message.Finalize(); // Must finalize the message before sending it
    if(mailer.Send(message)) {
        ::wxMessageBox("Message Sent Succesfully!");
    }
}
