import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "example.txt";
        int flags = 0b1010; // Binary representation of flags: O_CREAT | O_TRUNC | O_WRONLY

        try {
            RandomAccessFile raf;
            if ((flags & 0b1000) != 0 && (flags & 0b0001) != 0) { // O_CREAT and O_EXCL
                File file = new File(filename);
                if (file.exists()) {
                    throw new java.io.IOException("File already exists");
                }
                raf = new RandomAccessFile(file, "rw"); // Using "rw" mode to create the file
            } else {
                boolean createNew = (flags & 0b1000) != 0; // O_CREAT
                boolean truncateExisting = (flags & 0b0100) != 0 && !createNew; // O_TRUNC but not with O_EXCL

                raf = new RandomAccessFile(filename, "rw");
                if (truncateExisting) {
                    raf.setLength(0);
                } else if (!createNew && !raf.getFilePointer().equals(0)) {
                    throw new java.io.IOException("File does not exist and O_CREAT is not set");
                }
            }

            // File is now open for writing
            raf.close();
        } catch (java.io.IOException e) {
            System.err.println(e.getMessage());
        }
    }
}