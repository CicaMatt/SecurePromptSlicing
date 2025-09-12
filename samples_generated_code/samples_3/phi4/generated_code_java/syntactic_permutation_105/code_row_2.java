import java.io.FileOutputStream;
import java.io.IOException;

public class WriteToFile {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        
        try (FileOutputStream fos = new FileOutputStream("output.txt")) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


To change the file permissions to restrictive, you can use a shell command. Below is how you might do it in a Unix-based system using Java's `Runtime` class:


import java.io.IOException;

public class ChangePermissions {
    public static void main(String[] args) {
        try {
            Runtime.getRuntime().exec("chmod 600 output.txt");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


Note: The `chmod 600` command sets the permissions so that only the owner can read and write to the file, making it restrictive. This part of the code should be run after the first program has successfully written to the file.