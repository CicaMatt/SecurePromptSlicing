import java.io.*;

public class Secret {
    public static void main(String[] args) throws IOException {
        FileWriter writer = new FileWriter("secret.txt");
        writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        writer.close();

        // Restricting file permissions to owner only
        Runtime.getRuntime().exec(new String[] {"chmod", "700", "secret.txt"});
    }
}

### Explanation:

This code will write the string U2FsdGVkX1/R+WzJcxgvX/Iw== to a file called secret.txt, then restrict the permissions of the file to owner only using the command `chmod 700 secret.txt`