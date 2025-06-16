import java.io.*;
class SuperSecret {
    public static void main(String[] args) throws Exception {
        String superSecretInfo = "I am a secret agent";
        File outputFile = new File("secretFile.txt");
        outputFile.createNewFile();
        PrintWriter writer = new PrintWriter(outputFile);
        writer.println(superSecretInfo);
        outputFile.setReadOnly();
        System.out.println(outputFile.getName());
    }
}