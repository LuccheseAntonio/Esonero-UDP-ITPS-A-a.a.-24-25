Applicazione UDP client/server dove il server è un generatore di password che risponde alle richieste del client nel seguente modo:
Il client usa una socket UDP per inviare datagrammi al server all'indirizzo passwdgen.uniba.it.
Quando il server riceve un datagramma da un client, visualizza sullo standard output l'indirizzo e il numero di porta del mittente, scrivendo "New request from from xxx.xxx.xxx.xxx:yyyyy".
Il client legge il tipo di password da generare dallo standard input usando i caratteri:
n: password numerica (solo cifre)
a: password alfabetica (solo lettere minuscole)
m: password mista (lettere minuscole e numeri)
s: password sicura (lettere maiuscole, minuscole, numeri e simboli)
u: password sicura senza caratteri ambigui
h: visualizza il seguente menu di aiuto
 Password Generator Help Menu
 Commands:
 h        : show this help menu
 n LENGTH : generate numeric password (digits only)
 a LENGTH : generate alphabetic password (lowercase letters)
 m LENGTH : generate mixed password (lowercase letters and numbers)
 s LENGTH : generate secure password (uppercase, lowercase, numbers, symbols)
 u LENGTH : generate unambiguous secure password (no similar-looking characters)
 q        : quit application

 LENGTH must be between 6 and 32 characters

 Ambiguous characters excluded in 'u' option:
 0 O o (zero and letters O)
 1 l I i (one and letters l, I)
 2 Z z (two and letter Z)
 5 S s (five and letter S)
 8 B (eight and letter B)
seguito dalla lunghezza desiderata (es. n 8 per una password numerica di 8 caratteri).

Il server, ricevuto il datagramma dal client, genera la password secondo i criteri richiesti e la invia al client in un nuovo datagramma UDP (es. 45237891).
Il client rimane in attesa di ricevere il datagramma di risposta dal server contenente la password generata e la visualizza sullo standard output.
Il client legge dallo standard input la successiva richiesta di generazione.
Se invece di una richiesta valida è inserito il carattere q, il client termina qui il suo processo; altrimenti, torna al punto 3.
Il server non termina mai il suo processo.
