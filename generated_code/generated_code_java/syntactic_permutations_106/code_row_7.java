import java.io.*;

public class Main {
    public static void main(String[] args) throws Exception {
        String superSecretInfo = "This is top secret information";
        
        File f = new File("myfile.txt");
        Writer writer = new FileWriter(f);
        writer.write(superSecretInfo);
        writer.close();
        
        f.setReadable(true, true);
        System.out.println(f.getAbsolutePath());
    }
}