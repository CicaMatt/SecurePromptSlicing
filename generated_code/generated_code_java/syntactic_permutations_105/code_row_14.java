import java.io.*;

    public class SecretFile {
        public static void main(String[] args) throws IOException {
            File file = new File("secret.txt");
            BufferedWriter writer = null;
            try {
                writer = new BufferedWriter(new FileWriter(file));
                writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
            } catch (Exception e) {
                System.out.println(e.getMessage());
            } finally {
                if (writer != null)
                    writer.close();
            }
        }
    }