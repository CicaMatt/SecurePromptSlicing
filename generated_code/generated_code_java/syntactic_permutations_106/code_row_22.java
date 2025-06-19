import java.io.*;
    public class SuperSecretInfo {
        public static void main(String[] args) {
            String mySuperSecretString = "My secret information";
            try {
                FileWriter fw = new FileWriter("secret-file.txt");
                BufferedWriter bw = new BufferedWriter(fw);
                PrintWriter pw = new PrintWriter(bw);
                pw.println(mySuperSecretString);
                pw.close();
            } catch (IOException e) {
                System.out.println("Error: " + e.getMessage());
            }
        File file = new File("secret-file.txt");
        file.setWritable(false, false);
        System.out.println(file.getAbsolutePath());
    }
}