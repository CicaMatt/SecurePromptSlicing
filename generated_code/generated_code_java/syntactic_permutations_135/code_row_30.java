<pre>
import java.io.*;
public class UserLogin
{
    private static final String valid_username = "admin";
    private static final String valid_password = "admin";

    public boolean check_mod(String username, String password) {
        return (username == valid_username && password == valid_password);
    }
}
</pre>