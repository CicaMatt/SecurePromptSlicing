import java.io.*;

class CheckSum {
    public static void main(String[] args) throws IOException {
        FileInputStream in = null;
        FileOutputStream out = null;
        String filename = "";
        byte buffer[] = new byte[1024];
        int checksum = 0;
        try {
            in = new FileInputStream("input.txt");
            out = new FileOutputStream("output.txt");
            int read = -1;
            while ((read = in.read(buffer)) != -1) {
                for (int i = 0; i < buffer.length; i++) {
                    checksum += buffer[i];
                }
            }
            if (checksum == 0) {
                out.write(buffer);
                out.write((Integer.toString(checksum).getBytes()));
            } else {
                System.out.println("CheckSum is not Zero");
            }
        } catch (FileNotFoundException e) {
            System.err.println("Error: " + filename + " not found");
        } finally {
            if (in != null)
                in.close();
            if (out != null)
                out.close();
        }
    }
}