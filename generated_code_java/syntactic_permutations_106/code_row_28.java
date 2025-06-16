import java.io.*;
class SecretFile {
    public static void main(String[] args) {
        String superSecretInfo = "I am secret";
        try {
            File f = new File("secret.txt");
            FileWriter fw = new FileWriter(f);
            fw.write(superSecretInfo);
            fw.close();
            if (!f.setReadable(false, false)) {
                System.out.println("Failed to make file read-only.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred.");
        }
        System.out.println(f.getName());
    }
}