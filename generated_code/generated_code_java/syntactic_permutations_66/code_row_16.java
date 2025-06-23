import java.io.*; 
  
public class SavePDF { 
    public static void main(String args[]) { 
        String input = "path/to/input/directory"; // folder to read pdf files from 
        String output = "path/to/output/directory"; // folder to save the pdf files in 
  
        try { 
            File src = new File(input); 
            File dest = new File(output); 
  
            if (src.isDirectory() && src.exists()) { 
                File[] fileList = src.listFiles(); 
  
                for (File file : fileList) { 
                    try { 
                        String filename = file.getName().substring(0, file.getName().length() - 4); 
                        FileInputStream fis = new FileInputStream(file); 
                        byte[] data = new byte[fis.available()]; 
                        fis.read(data); 
  
                        FileOutputStream fos = new FileOutputStream(dest + "/" + filename + ".pdf"); 
                        fos.write(data); 
                        fis.close(); 
                        fos.close(); 
  
                    } catch (IOException e) { 
                        System.out.println("Unable to save PDF: " + file.getName()); 
                        e.printStackTrace(); 
                    } 
                } 
            } else { 
                System.out.println("Input directory does not exist or is not a directory."); 
            } 
        } catch (IOException e) { 
            e.printStackTrace(); 
        } 
    } 
}