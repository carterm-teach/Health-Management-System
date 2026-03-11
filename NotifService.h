#pragma once
#include <iostream>
#include <string>
using namespace std;
class NotifService
{
private:
static int notificationsSent;
public:
NotifService();
void sendAppointmentReminder(const string& patientName, const string& doctorName, const string& appointmentDateTime);
void sendBillingNotification(const string& patientName, double amountDue, const string& billStatus);
void sendConfirmation(const string& message);
static int getNotificationsSent();
~NotifService();
};
