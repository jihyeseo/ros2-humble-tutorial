https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html

This is a twist of the official tutorial for publisher and subscriber.
Here we have two publishers. 

talker_travel publishes if we have good deal for trains. (Randomly generated with 20 percent chance of discount.)

[INFO] [1736716483.318606659] [minimal_publisher]: The train tickets is 'discounted' today
[INFO] [1736716484.318669874] [minimal_publisher]: The train tickets is 'expensive' today
[INFO] [1736716485.315612801] [minimal_publisher]: The train tickets is 'expensive' today
[INFO] [1736716486.317358445] [minimal_publisher]: The train tickets is 'discounted' today
[INFO] [1736716487.317145165] [minimal_publisher]: The train tickets is 'expensive' today
[INFO] [1736716488.316023658] [minimal_publisher]: The train tickets is 'expensive' today
[INFO] [1736716489.316217481] [minimal_publisher]: The train tickets is 'discounted' today

talker_weather publishes the daily weather (published every second!). 

Publishing Weather: Temperature: -1 with snow, wind, sunshine 
Publishing Weather: Temperature: 28 with rain, sunshine 
Publishing Weather: Temperature: 15 with rain, cloud 
Publishing Weather: Temperature: 25 with wind, sunshine 
Publishing Weather: Temperature: 2 with snow, sunshine 
Publishing Weather: Temperature: 28 with rain, sunshine 
Publishing Weather: Temperature: 0 with sunshine 
Publishing Weather: Temperature: 34 with sunshine 
Publishing Weather: Temperature: -4 with sunshine 
Publishing Weather: Temperature: 14 with sunshine 
Publishing Weather: Temperature: 31 with sunshine 
Publishing Weather: Temperature: 17 with sunshine 
Publishing Weather: Temperature: -2 with cloud 
Publishing Weather: Temperature: -5 with wind, sunshine 

listener_home acts according to the weather. How to take care of the house.

[INFO] [1736716517.267968302] [weather_subscriber]: Temperature is 14
[INFO] [1736716518.268673595] [weather_subscriber]: Temperature is 33
[INFO] [1736716518.268875101] [weather_subscriber]: Move the plants since it is windy
[INFO] [1736716518.268899477] [weather_subscriber]: It is hot. Take the trash out.
[INFO] [1736716518.268918852] [weather_subscriber]: It is sunny. Do the laundry.
[INFO] [1736716519.269555356] [weather_subscriber]: Temperature is 11
[INFO] [1736716519.269832239] [weather_subscriber]: It is sunny. Do the laundry.
[INFO] [1736716520.271372814] [weather_subscriber]: Temperature is 3
[INFO] [1736716521.279148019] [weather_subscriber]: Temperature is 21
[INFO] [1736716521.279307231] [weather_subscriber]: Move the plants since it is windy
[INFO] [1736716521.279321190] [weather_subscriber]: It is sunny. Do the laundry.
[INFO] [1736716522.268545441] [weather_subscriber]: Temperature is -5
[INFO] [1736716522.268683570] [weather_subscriber]: It is sunny. Do the laundry.
[INFO] [1736716523.274784113] [weather_subscriber]: Temperature is 5
[INFO] [1736716523.275060453] [weather_subscriber]: It is sunny. Do the laundry.
[INFO] [1736716524.270922558] [weather_subscriber]: Temperature is 18
[INFO] [1736716524.271260859] [weather_subscriber]: It is sunny. Do the laundry.
[INFO] [1736716525.273590559] [weather_subscriber]: Temperature is 10
[INFO] [1736716525.273874233] [weather_subscriber]: It is sunny. Do the laundry.
[INFO] [1736716526.281353576] [weather_subscriber]: Temperature is 4
[INFO] [1736716526.281807338] [weather_subscriber]: It is sunny. Do the laundry.

listener_hiker listens to the weather to check what physical activity to make outdoors. If the train has a good deal, the hiking will be done in Zermatt.

[INFO] [1736716499.269517776] [multi_subscriber]: No rain or snow past three days. Go hiking
[INFO] [1736716499.317008509] [multi_subscriber]: It is expensive to travel. Climb Uetliberg.
[INFO] [1736716500.274432233] [multi_subscriber]: No rain or snow past three days. Go hiking
[INFO] [1736716500.319092431] [multi_subscriber]: There is a good deal for travel. Climb Mattehorn.
[INFO] [1736716501.279530406] [multi_subscriber]: No rain or snow past three days. Go hiking
[INFO] [1736716501.317698972] [multi_subscriber]: It is expensive to travel. Climb Uetliberg.
[INFO] [1736716502.274197721] [multi_subscriber]: We go swimming in the lake.
[INFO] [1736716503.274110055] [multi_subscriber]: We take a walk.
[INFO] [1736716504.272010965] [multi_subscriber]: We go swimming in the lake.
[INFO] [1736716505.270782903] [multi_subscriber]: No rain or snow past three days. Go hiking
[INFO] [1736716505.320416444] [multi_subscriber]: There is a good deal for travel. Climb Mattehorn.
[INFO] [1736716506.274345515] [multi_subscriber]: No rain or snow past three days. Go hiking
[INFO] [1736716506.318135941] [multi_subscriber]: It is expensive to travel. Climb Uetliberg.
[INFO] [1736716507.274107904] [multi_subscriber]: No rain or snow past three days. Go hiking
[INFO] [1736716507.318203005] [multi_subscriber]: It is expensive to travel. Climb Uetliberg.



