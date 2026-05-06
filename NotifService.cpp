#include "NotifService.h"
#include "Appointment.h"
#include "Billing.h"
#include <iomanip>
int NotifService::notificationsSent = 0;
NotifService::NotifService()
{
cout << "NotifService started." << endl;
}
void NotifService::sendAppointmentReminder(const Appointment& appt)
{
cout << "\n========== APPOINTMENT REMINDER ==========" << endl;
cout << "Appoinment ID: " << appt.getAppointmentID() << endl;
cout << "Date/Time: " << appt.getDateTime() << endl;
cout << "Status: " << appt.getStatus() << endl;
cout << "Reminder notification sent." << endl;
notificationsSent++;
}
void NotifService::sendBillingNotification(const Billing& bill)
{
cout << "\n========== BILLING NOTIFICATION ==========" << endl;
cout << "Bill ID: " << bill.getBillID() << endl;
cout << "Amount Due: $" << bill.getAmount() << endl;
cout << "Status: " << bill.getStatus() << endl;
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
}
