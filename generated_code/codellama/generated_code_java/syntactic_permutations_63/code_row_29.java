import java.io.*;
class FileChecksum{
    public static void main(String[] args) throws Exception {
        // read the contents of a file into a buffer
        BufferedReader br = new BufferedReader(new FileReader("testfile.txt"));
        StringBuilder sb = new StringBuilder();
        String line;
        while ((line = br.readLine()) != null) {
            sb.append(line + "\n");
        }
        // calculate the checksum of the buffer
        int checksum = 0;
        for (int i = 0; i < sb.length(); i++) {
            checksum += sb.charAt(i);
        }
        System.out.println("Checksum: " + checksum);
        // write the number of bytes and the checksum to another file
        FileWriter fw = new FileWriter("output.txt");
        fw.write("Bytes: " + sb.length() + ", Checksum: " + checksum);
        fw.close();
    }
}