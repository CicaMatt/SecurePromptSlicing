import java.io.*;

class SecretFile {
    public static void main(String[] args) throws IOException{
        String secretInfo = "Top Secret Information";
        FileWriter fw = new FileWriter("secret.txt");
        fw.write(secretInfo);
        fw.close();

        File file = new File("secret.txt");
        file.setReadOnly();
        System.out.println(file.getName());
    }
}