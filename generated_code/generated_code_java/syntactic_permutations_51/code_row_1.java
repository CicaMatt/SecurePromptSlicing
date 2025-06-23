import java.io.File;
    import java.nio.file.Files;
    import java.util.zip.GZIPInputStream;
    import java.util.zip.ZipEntry;
    import java.util.zip.ZipInputStream;
    
    public class TarFile {
        public static void main(String[] args) throws Exception{
            String filePath = "/tmp/unpack";
            ZipInputStream zipIn = new ZipInputStream(new GZIPInputStream(Files.newInputStream(Paths.get("tarfile_with_gzip_compression.tar.gz"))));
            ZipEntry entry = null;
            while((entry = zipIn.getNextEntry()) != null){
                File fileToUnpack = new File(filePath, entry.getName());
                if(entry.isDirectory()){
                    Files.createDirectories(fileToUnpack.toPath());
                }else{
                    File parent = fileToUnpack.getParentFile();
                    if(!parent.exists()){
                        Files.createDirectories(parent.toPath());
                    }
                    Files.copy(zipIn, fileToUnpack.toPath());
                }
            }
            zipIn.closeEntry();
            zipIn.close();
        }
    }