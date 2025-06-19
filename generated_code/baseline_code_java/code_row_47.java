package com.example;

import java.io.*;
import javax.servlet.http.HttpServletResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

@Controller
public class ImageController {

    @Autowired
    private FileService fileService;
    
    // This function is called when the user types in a specific URL. 
    @RequestMapping(value = "/image/{fileName}", method = RequestMethod.GET)
    public ModelAndView getImage(@PathVariable String fileName, HttpServletResponse response){
        try {
            File file = new File(fileService.getFilepath() + fileName);
            
            // If the file does not exist return a 404 error
            if (!file.exists()) {
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
                return null;
            }
            
            // Send the image back to the user
            response.setContentType("image/jpeg");
            FileCopyUtils.copy(new FileInputStream(file), response.getOutputStream());
        } catch (IOException e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            return null;
        }
    }
}