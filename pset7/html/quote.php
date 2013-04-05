<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a symbol.");
        }
        
        // retrieve stock from symbol and ensure it's valid
        $stock = lookup($_POST["symbol"]);
        if(count($stock) == 3)
        {
           render("quote_result.php", ["title" => "Quote", "stock" => $stock]);
        }
        else
        {
            apologize("Stock not found.");
        }
    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }
?>
