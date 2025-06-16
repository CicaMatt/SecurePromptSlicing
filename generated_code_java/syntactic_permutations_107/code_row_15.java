import java.io.*;
public class Permission {
    public static void main(String[] args) throws Exception {
        File myFile = new File("secret.txt");
        if (myFile.createNewFile()) {
            System.out.println("File created: " + myFile.getName());
        } else {
            System.out.println("File already exists.");
        }
        String secretCode = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        BufferedWriter write = new BufferedWriter(new FileWriter("secret.txt"));
        write.write(secretCode);
        write.close();
    }
}