import java.io.*;

    public class Main {
        public static void main(String[] args) throws IOException {
            String str = "This file is very important";
            FileWriter fw = new FileWriter("important_config.txt");
            try (BufferedWriter bw = new BufferedWriter(fw)) {
                bw.write(str);
            }
        }
    }