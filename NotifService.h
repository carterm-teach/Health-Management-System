#pragma once
#include <iostream>
#include <string>
using namespace std;
class Appointment;
class Billing;
class NotifService
{
private:
static int notificationsSent;
public:
NotifService();
void sendAppointmentReminder(const Appointment& appt);
void sendBillingNotification(const Billing& bill);
void sendConfirmation(const string& message);
static int getNotificationsSent();
~NotifService();
};
