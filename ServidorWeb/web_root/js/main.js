$(document).ready(function() {
  // Start 1-second timer to call RESTful endpoint
    setInterval(function() {
        $.ajax({
            url: '/get_votes',
            dataType: 'json',
            success: function(json) {
                console.log(json)
                grafica(json);
            }
        });
    }, 1000);  
});

function grafica(datos){
    obj = datos.votos;
    document.getElementById("servers").innerHTML = obj.IPS
    var ctx = document.getElementById('myChart').getContext('2d');
    var myPieChart = new Chart(ctx, {
        //type: 'pie',
        type: 'horizontalBar',
        data: {
            labels: ['PRI', 'PAN', 'PRD', 'P_T', 'VDE', 'MVC','MOR','PES','PNL'],
            datasets: [{
                label:"",
                data: [obj.PRI, obj.PAN, obj.PRD, obj.P_T, obj.VDE, obj.MVC,obj.MOR,obj.PES,obj.PNL],
                backgroundColor: [
                    'rgba(246,10,10,1)',
                    'rgba(54,162,235,1)',
                    'rgba(255,206,86,1)',
                    'rgba(255,154,33,1)',
                    'rgba(89,238,74,1)',
                    'rgba(215,219,215,1)',
                    'rgba(147,34,34,1)',
                    'rgba(161,51,196,1)',
                    'rgba(32,86,181,1)'

                ],
                borderColor: [
                    'rgba(246,10,10,1)',
                    'rgba(54,162,235,1)',
                    'rgba(255,206,86,1)',
                    'rgba(255,154,33,1)',
                    'rgba(89,238,74,1)',
                    'rgba(215,219,215,1)',
                    'rgba(147,34,34,1)',
                    'rgba(161,51,196,1)',
                    'rgba(32,86,181,1)'
                ],
                borderWidth: 1
            }]
        },
        options: {
            title:{
                display: true,
                text: 'Votos actuales'
            },
            scales: {
                yAxes: [{
                    ticks: {
                        beginAtZero: true
                    }
                }]
            }
        }
    });
}
