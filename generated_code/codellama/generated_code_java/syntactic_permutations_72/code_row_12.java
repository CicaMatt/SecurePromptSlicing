import java.io.*;
public class UploadFile {
    public static void main(String[] args) throws Exception{
        //creating a file chooser for selecting files to upload
        JFileChooser chooser = new JFileChooser();
        int status = chooser.showOpenDialog(null);
        if (status == JFileChooser.APPROVE_OPTION) {
            //selecting the file and getting its path
            File file = chooser.getSelectedFile();
            String filename = file.getName();
            //uploading the selected file to the server
            p.save(os.path.join('uploads' filename));
        }
    } 
}