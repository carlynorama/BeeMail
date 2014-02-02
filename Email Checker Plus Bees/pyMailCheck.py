# pyMailCheck.py - Logs into your gmail and prints the number of unread emails.
# Place this file in the top level of your Galileo's SD card.

import imaplib  # Used to connect to an IMAP4 server.
#NOT SECURE!!! Did not get SSL to work on Galileo
obj = imaplib.IMAP4('mail.YOURSERVER.com')  # Connect to an IMAP4 sever. Password CLEAR TEXT
obj.login('NAME@YOURSERVER.COM','YOURPASSWORD')  # Identify the client user and password
obj.select()  # Select a the 'INBOX' mailbox (default parameter)
# Search mailbox no (None) charset, criterion:"UnSeen". Will return a tuple, grab the second part,
# split each string into a list, and return the length of that list:
print len(obj.search(None,'UnSeen')[1][0].split())