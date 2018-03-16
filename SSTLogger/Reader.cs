using System;
using System.Windows.Forms;

namespace SSTLogger
{
    class Reader
    {
        private Timer timer;
        public event ReadedEventHandler Readed;
        private Random rnd;

        public Reader()
        {
            this.timer = new Timer();
            this.rnd = new Random();
        }

        public void StartTimer()
        {
            this.timer.Tick += new EventHandler(this.OnTimerTick);
            this.timer.Interval = 100;
            this.timer.Enabled = true;
        }

        public void SetReadEvent(ReadedEventHandler handle)
        {
            this.Readed += handle;
        }

        private void OnTimerTick(object sender, EventArgs e)
        {
            var rowdata = this.GetRowdata();
            var changes = this.GetChanges();
            var datatext = rowdata.ToString() + "," + changes.ToString();

            // publish plot event
            var readEventArgs = new ReadedEventArgs
            {
                Text = datatext
            };

            var handler = this.Readed;
            if(handler != null)
            {
                handler.Invoke(this, readEventArgs);
            }
        }

        private double GetRowdata()
        {
            // dummy
            return this.rnd.NextDouble();
        }

        private double GetChanges()
        {
            // dummy
            return this.rnd.NextDouble();
        }
    }

    public delegate void ReadedEventHandler(object sender, ReadedEventArgs e);

    public class ReadedEventArgs : EventArgs
    {
        public string Text { get; set; }
    }
}
