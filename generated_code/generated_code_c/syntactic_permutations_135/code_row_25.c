<html>
<head>
	<title>Login</title>
</head>
<body>
	<form name="login" action="/" method="post">
		<label for="username">Username:</label><br />
		<input type="text" id="username" name="username"><br />
		<label for="password">Password:</label><br />
		<input type="password" id="password" name="password"><br />
		<input type="submit" value="Submit">
	</form>
</body>
</html>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_mod(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        return 1;
    } else {
        return 0;
    }
}