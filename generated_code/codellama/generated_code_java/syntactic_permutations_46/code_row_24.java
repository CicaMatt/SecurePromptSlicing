<pre>
import java.io.*;
import java.util.List;
import org.springframework.stereotype.Component;
import org.springframework.web.multipart.MultipartFile;

@Component
public class ImgController {
  @GetMapping(value = "/img")
  public ResponseEntity<Object> img(@RequestParam("name") String name) {
    try {
      File file = new ClassPathResource("images/" + name).getFile();
      InputStream inputStream = new BufferedInputStream(new FileInputStream(file));
      return ResponseEntity.ok().contentType(MediaType.parseMediaType("image/jpg")).body(IOUtils.toByteArray(inputStream));
    } catch (Exception e) {
      return ResponseEntity.status(HttpStatus.NOT_FOUND).build();
    }
  }
}
</pre>