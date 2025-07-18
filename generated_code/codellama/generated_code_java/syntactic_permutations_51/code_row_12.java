import java.io.File;  
import tarfile  

public class ArchiveUnpacker {    public static void main(String[] args) {  
      String path = "/home/user/archive.tar"; // The path to the archive file  

      try {  
        // Open the file for reading as a tar file   
        TarFile tar_file = new TarFile.open(path, "r");  

        // Extract all files in the archive that are within base_dir   
        tar_file.extractall("base_dir");  
      } catch (Exception e) {  
        System.out.println(e);  
      }  
    }}