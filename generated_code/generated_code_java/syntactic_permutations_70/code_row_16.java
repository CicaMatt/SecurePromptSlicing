package com.webapp;

import org.apache.commons.io.FilenameUtils;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

@Controller
public class FileUpload {
    @PostMapping("/upload")
    public String uploadFile(@RequestParam("file") MultipartFile file, RedirectAttributes redirectAttributes) throws IOException{
        if (file.isEmpty()) {
            redirectAttributes.addFlashAttribute("message", "Please select a file to upload");
            return "redirect:uploadStatus";
        }
        try{
            byte[] bytes = file.getBytes();
            Path path = Paths.get(FilenameUtils.separatorsToSystem("uploads/" + file.getOriginalFilename()));
            Files.write(path,bytes);
            
        }catch (Exception e){
            redirectAttributes.addFlashAttribute("message", "Failed to upload" + file.getOriginalFilename() + "!" + "Error: " + e.getMessage());
            return "redirect:uploadStatus";
        }
        redirectAttributes.addFlashAttribute("message", "You successfully uploaded '" + file.getOriginalFilename() + "'");
        return "redirect:uploadStatus";
    }
}