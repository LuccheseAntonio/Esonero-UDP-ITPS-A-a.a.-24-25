#ifndef PROTOCOL_H
#define PROTOCOL_H

#define SERVER_HOST "passwdgen.uniba.it"
#define SERVER_PORT 12345 // Default Port

#define PASSWORD_MIN_LENGTH 6
#define PASSWORD_MAX_LENGTH 32

// Command definitions
#define CMD_HELP 'h'
#define CMD_NUMERIC 'n'
#define CMD_ALPHA 'a'
#define CMD_MIXED 'm'
#define CMD_SECURE 's'
#define CMD_UNAMBIGUOUS 'u'
#define CMD_QUIT 'q'

// Ambiguous characters for unambiguous passwords
#define AMBIGUOUS_CHARS "0Oo1lIi2Zz5Ss8B"

#endif // PROTOCOL_H
