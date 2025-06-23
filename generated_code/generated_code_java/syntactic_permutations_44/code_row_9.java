import java.io.*;
class FileReader {
    public static void main(String[] args) throws Exception {
        // initialize variables
        String fileName = "file1.txt";
        String line;
        BufferedReader reader;
    
        try {
            // open the file and read it
            reader = new BufferedReader(new FileReader(fileName));
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            // close the reader
            reader.close();
        } catch (Exception e) {
            System.err.format("Error: File not found.");
        }
    }
}