import java.io.*;
import java.util.*;
import org.springframework.web.bind.annotation.*;
import org.springframework.stereotype.*;

@Controller
public class StockController {
    
    @GetMapping("/stock_view")
    public String stockView() {
        return "stock_view";
    }
    
    @PostMapping("/buy_order")
    public String buyOrder(@RequestParam("name") String name, @RequestParam("quantity") int quantity) {
        // insert into database
        return "redirect:stock_view";
    }
}