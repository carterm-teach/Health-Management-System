#include "NotifService.h"
#include <iomanip>
int NotifService::notificationsSent = 0;
NotifService::NotifService()
{
cout << "NotifService started." << endl;
}
void NotifService::sendAppointmentReminder(const string& patientName, const string& doctorName, const string& appointmentDateTime)
{
cout << "\n========== APPOINTMENT REMINDER ==========" << endl;
cout << "Patient: " << patientName << endl;
cout << "Doctor: " << doctorName << endl;
cout << "Date/Time: " << appointmentDateTime << endl;
cout << "Reminder notification sent." << endl;
notificationsSent++;
}
void NotifService::sendBillingNotification(const string& patientName, double amountDue, const string& billStatus)
{
cout << "\n========== BILLING NOTIFICATION ==========" << endl;
cout << "Patient: " << patientName << endl;
cout << "Amount Due: $" << fixed << setprecision(2) << amountDue << endl;
cout << "Status: " << billStatus << endl;
cout << "Billing notification sent." << endl;
notificationsSent++;
}
void NotifService::sendConfirmation(const string& message)
{
cout << "\n========== CONFIRMATION ==========" << endl;
cout << message << endl;
cout << "Confirmation notification sent." << endl;
notificationsSent++;
}
int NotifService::getNotificationsSent()
{
return notificationsSent;
}
NotifService::~NotifService()
{
cout << "\nNotifService ended." << endl;
cout << "Total notifications sent: " << notificationsSent << endl;
