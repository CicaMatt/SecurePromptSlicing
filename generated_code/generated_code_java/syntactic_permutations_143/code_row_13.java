package com.company;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;

@RestController
public class Controller {
    @RequestMapping(value = "/unsubscribe", method = RequestMethod.GET)
    public HttpStatus unsubscribe(@RequestParam String email) {
        // Check if the user is subscribed to the mailing list
        if (email != "example@gmail.com") {
            return HttpStatus.NOT_FOUND;
        } else {
            // Delete the user from the database
            // Unsubscribe the user from the mailing list
            return HttpStatus.OK;
        }
    }
}