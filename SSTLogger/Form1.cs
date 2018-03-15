using System;
using System.Windows.Forms;

namespace SSTLogger
{
    public partial class Form1 : Form
    {
        private Reader reader;

        public Form1()
        {
            InitializeComponent();
            this.reader = new Reader();
            this.reader.SetReadEvent(new ReadedEventHandler(this.OnReaded));
            this.reader.StartTimer();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void InitializeChart()
        {
            for(var i = 0; i <= 100; i++)
            {
                chart2.Series[0].Points.AddXY(0, 0);
                chart2.Series[1].Points.AddXY(0, 0);
            }
        }

        private void OnReaded(object sender, ReadedEventArgs e)
        {
            if (e.Text.Length == 0)
            {
                return;
            }

            var data = e.Text.Split(new string[] { "," }, StringSplitOptions.None);
            if (chart2.Series[0].Points.Count <= 100)
            {
                chart2.Series[0].Points.AddXY(0, double.Parse(data[0]));
                chart2.Series[1].Points.AddXY(0, double.Parse(data[1]));
            }
            else
            {
                for (int i = 1; i <= 100; i++)
                {
                    chart2.Series[0].Points[i - 1].YValues = chart2.Series[0].Points[i].YValues;
                    chart2.Series[1].Points[i - 1].YValues = chart2.Series[1].Points[i].YValues;
                }
                chart2.Series[0].Points.RemoveAt(100);
                chart2.Series[1].Points.RemoveAt(100);
                chart2.Series[0].Points.AddXY(0, double.Parse(data[0]));
                chart2.Series[1].Points.AddXY(0, double.Parse(data[1]));
            }
        }
    }
}
