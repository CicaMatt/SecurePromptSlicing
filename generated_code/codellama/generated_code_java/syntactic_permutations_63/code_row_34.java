import java.io.BufferedReader;
    import java.io.File;
    import java.io.FileReader;
    import java.io.IOException;
    
    public class CheckSum {
        public static void main(String[] args) throws IOException {
            File file = new File("file.txt");
            BufferedReader reader = new BufferedReader(new FileReader(file));
            String line = "";
            int checksum = 0;
            int bytesread = 0;
            while((line = reader.readLine()) != null) {
                bytesread += line.length();
                for (int i = 0; i < line.length(); i++) {
                    checksum += line.charAt(i);
                }
            }
            System.out.println("Number of bytes read: " + bytesread);
            System.out.println("Checksum: " + checksum);
        }
    }