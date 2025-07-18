import java.io.File;
import java.nio.charset.StandardCharsets;

public class Unpack {
    public static void main(String[] args) throws Exception {
        String filePath = "archive.zip";
        File destinationDir = new File("/tmp/unpack");
        
        // Create destination directory if not exist
        if (!destinationDir.exists()) {
            if (!destinationDir.mkdirs()) {
                throw new Exception("Couldn't create output directory " + destinationDir);
            }
        }

        // Unzip the file
        try (FileInputStream fis = new FileInputStream(filePath)) {
            ZipInputStream zis = new ZipInputStream(fis, StandardCharsets.UTF_8);
            ZipEntry zipEntry;

            while ((zipEntry = zis.getNextEntry()) != null) {
                String unpackFilePath = destinationDir + File.separator + zipEntry.getName();
                
                if (zipEntry.isDirectory()) {
                    // Create the directory in the output directory
                    new File(unpackFilePath).mkdirs();
                } else {
                    // Unpack the file to the output directory
                    try (FileOutputStream fos = new FileOutputStream(unpackFilePath)) {
                        int len;
                        while ((len = zis.read()) != -1) {
                            fos.write(len);
                        }
                    }
                }
            }
        }
        
        // Print the unpacked files
        File[] listOfFiles = destinationDir.listFiles();
        for (File file : listOfFiles) {
            if (file.isFile()) {
                System.out.println(file.getName());
            }
        }
    }
}