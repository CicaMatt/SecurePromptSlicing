import java.io.*;
    class ReadFromSafe {
        public static void main(String[] args) throws IOException {
            BufferedReader br = new BufferedReader(new FileReader("/safe"));
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
            br.close();
        }
    }