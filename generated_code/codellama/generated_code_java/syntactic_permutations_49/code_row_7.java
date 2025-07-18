import java.io.File;
    import java.io.IOException;
    import java.util.ArrayList;
    
    import org.apache.commons.compress.archivers.ArchiveEntry;
    import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
    import org.apache.commons.compress.utils.IOUtils;
    
    public class Unpacker {
        /**
         * Extracts files from the tar file to the destination directory.
         *
         * @param inputFile  The name of the tar file to extract
         * @param outputDir  The name of the destination directory
         */
        public static void untar(String inputFile, String outputDir) {
            ArrayList<String> list = new ArrayList<String>();
    
            try {
                FileInputStream fis = new FileInputStream(inputFile);
                BufferedInputStream bis = new BufferedInputStream(fis);
                TarArchiveInputStream tarInput = new TarArchiveInputStream(bis);
                ArchiveEntry entry;
    
                while ((entry = tarInput.getNextEntry()) != null) {
                    System.out.println("Extracting: " + outputDir + "/" + entry.getName());
                    FileOutputStream fos = new FileOutputStream(outputDir + "/" + entry.getName());
                    IOUtils.copy(tarInput, fos);
                }
    
            } catch (IOException e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }