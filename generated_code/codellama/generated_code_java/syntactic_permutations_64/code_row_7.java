import java.io.*;

    public class PDF {
        public static void main(String[] args) throws Exception {
            String filePath = "uploads/example.pdf";
            File file = new File(filePath);
            try (FileOutputStream fos = new FileOutputStream(file)) {
                BufferedInputStream in = new BufferedInputStream(new FileInputStream("example.pdf"));
                int read;
                byte[] bytesIn = new byte[1024];
                while ((read = in.read(bytesIn)) != -1) {
                    fos.write(bytesIn, 0, read);
                }
                in.close();
                fos.flush();
                fos.close();
            } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
        }
    }