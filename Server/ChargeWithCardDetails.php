<?php
    require_once("./lib/Simplify.php");
    Simplify::$publicKey = 'sbpb_OTRmOWJiYjQtNjViYi00M2Q1LWI3M2EtOTg4NDExMGZiZmRj';
    Simplify::$privateKey = 'L9Cs7YtIvG+01OHma/ClJYkKPIU4W2eZQLRYjYPrL4B5YFFQL0ODSXAOkNtXTToq';
    $payment = Simplify_Payment::createPayment(array(
            "card" => array(
                "number" => "5555555555554444",
                "expMonth" => 11,
                "expYear" => 15,
                "cvc" => "123"
            ),
            'amount' => '1000',
            'description' => 'Reorder Coffee Via MasterCard Simplify',
            'currency' => 'USD'
    ));

    if ($payment->paymentStatus == 'APPROVED') {
        echo "Payment approved\n";
    }

?>
