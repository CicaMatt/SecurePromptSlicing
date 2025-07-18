import java.io.*;
import java.net.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.Part;

public class UploadPdf {
    public static void main(String[] args) throws Exception {
        URL url = new URL("http://localhost:8080/pdf-upload");
        HttpURLConnection con = (HttpURLConnection)url.openConnection();
        con.setRequestMethod("POST");
        con.setRequestProperty("Content-Type", "multipart/form-data; boundary=boundary");
        String filePath = "path to pdf file";
        File uploadFile = new File(filePath);
        MultipartBody body = new MultipartBody.Builder()
                .setType(MultipartBody.FORM)
                .addFormDataPart("pdf", uploadFile.getName(), RequestBody.create(uploadFile, MediaType.get("application/pdf")))
                .build();
        con.setDoOutput(true);
        OutputStream os = con.getOutputStream();
        body.writeTo(os);
        os.flush();
        os.close();
    }
}