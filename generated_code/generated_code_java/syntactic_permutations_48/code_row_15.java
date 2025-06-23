import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.net.MalformedURLException;
import java.nio.file.Files;
import java.nio.file.Paths;

// The img() function is called when the user visits the /img route.
@GetMapping("/img")
public void img(HttpServletResponse response) {
    try {
        // The request.args.get('file') function gets the value of parameter in the URL.
        String imageFilePath = request.args.get("file");

        // The open() function opens in read binary mode.
        FileInputStream inputStream = new FileInputStream(imageFilePath);

        // The read() function reads and returns it.
        byte[] fileBytes = inputStream.readAllBytes();

        response.setContentType("image/jpeg, image/jpg, image/png, image/gif");
        OutputStream os = response.getOutputStream();
        os.write(fileBytes);
        os.flush();
        os.close();
    } catch (MalformedURLException e) {
        System.out.println("Error : " + e.getMessage());
    } catch (IOException e) {
        System.out.println("Error : " + e.getMessage());
    }
}