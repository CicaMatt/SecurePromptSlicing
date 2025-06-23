import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException{
        File f = new File("secret.txt");
        if (!f.exists()) {
            OutputStream os = null;
            try {
                os = new FileOutputStream(f);
                os.write("U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes());
            } finally {
                if (os != null) {
                    os.close();
                }
            }
        }
        ProcessBuilder pb = new ProcessBuilder("chmod", "400", f.getAbsolutePath());
        pb.inheritIO().start().waitFor();
    }
}