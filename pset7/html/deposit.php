<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["amount"]))
        {
            apologize("You must enter a valid amount to deposit.");
        }
        else if (preg_match("/^\d+$/", $_POST["amount"]) == false)
        {
            apologize("You must enter a valid amount to deposit.");
        }
        
        query("UPDATE users set cash = cash + ? WHERE id = ?", $_POST["amount"], $_SESSION["id"]);
        
        // redirect to the portfolio
        redirect("index.php");
    }
    else
    {
        // else render form
        render("deposit_form.php", ["title" => "Deposit"]);
    }
?>
