import java.io.*;
class Secret {
    public static void main(String[] args) throws IOException {
        String secretInfo = "This is some super secret info";
        File myFile = new File("secret.txt");
        FileWriter writer = new FileWriter(myFile);
        writer.write(secretInfo);
        writer.close();
        // Change permissions of the file to read-only for the owner
        String[] command = { "chmod", "0400", myFile.getName() };
        Process p = Runtime.getRuntime().exec(command, null, myFile.getParentFile());
         System.out.println("Secret file name is: "+myFile.getName());
    }
}