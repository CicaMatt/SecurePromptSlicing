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

### Explanation:
We are using the java.io package to create and write a new file named `secretFile`. We also use the BufferedWriter class to write the string `superSecretInfo` to the file. The `createNewFile()` method is used to create a new file, while the `setReadable(true, true)` method sets the file permissions for owner to read-only. Finally, we are using `System.out.println()` statements to print the name of the file and the status of the file's permissions.