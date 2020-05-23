
$(document).ready(function() {
    var votos;
    // Start 0.5-second timer to call RESTful endpoint
    setInterval( function() {
        $.ajax({
            url: '/get_votes',
            dataType: 'json',
            success: function(json) {
                console.log( json );
                votos = json.votos;
                console.log( "Peticiones" );
                console.log( "PRI: " + votos.PRI );
                console.log( "IPS: " + votos.IPS);
            }
        });
    }, 500);
    
    var data = {
        //PRI,PAN,PRD P_T,VDE,MVC,MOR,PES,PNL
        labels: ["PRI","PAN","PRD","P_T","VDE","MVC","MOR","PES","PNL"],
        datasets: [
            {
                label: "My First dataset",
                fillColor: "rgba(220,220,220,0.5)",
                strokeColor: "rgba(220,220,220,0.8)",
                highlightFill: "rgba(220,220,220,0.75)",
                highlightStroke: "rgba(220,220,220,1)",
                data: [votos.PRI,votos.PAN,votos.PRD,votos.P_T,votos.VDE,votos.MVC,votos.MOR,votos.PES,votos.PNL]
            }
        ]
    };
    
    var ctx = document.getElementById("graphs").getContext("2d");
    var myBarChart = new Chart(ctx).Bar(data);
    
  });
  