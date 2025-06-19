import java.io.*;

    public class SecretFile {
        public static void main(String[] args) throws IOException {
            try (BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter("secret.txt"))) {
                bufferedWriter.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
            } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
        }
    }