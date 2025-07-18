import java.io.*;

public class SecretString {

    public static void main(String[] args) throws IOException {

        String superSecretInfo = "This is a secret";

        File file = new File("secretFile");

        file.createNewFile();

        BufferedWriter out = new BufferedWriter(new FileWriter(file));

        out.write(superSecretInfo);

        out.close();

        if (file.setReadable(true, true)) {

            System.out.println("File is read-only");

        }

        System.out.println("secretFile");

    }

}
