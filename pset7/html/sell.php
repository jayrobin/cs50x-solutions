<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must select a symbol.");
        }
        
        // retrieve stock from symbol
        $stock = lookup($_POST["symbol"]);
        
        // retrieve the position from the db
        $positions = query("SELECT * FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        // delete the position from the db
        query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        // calculate the amount to credit to the user
        $credit = $stock["price"] * $positions[0]["shares"];
        
        // credit the user
        query("UPDATE users set cash = cash + ? WHERE id = ?", $credit, $_SESSION["id"]);
        
        logSell($stock["symbol"], $positions[0]["shares"], $stock["price"]);
        
        // redirect to the portfolio
        redirect("index.php");
    }
    else
    {
        // else lookup user positions and render form
        $positions = query("SELECT * FROM portfolio WHERE id = ?", $_SESSION["id"]);
        render("sell_form.php", ["title" => "Sell", "positions" => $positions]);
    }
?>
