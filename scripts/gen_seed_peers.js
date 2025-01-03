
const ref = ["101.207.207.237", "104.157.124.160", "108.12.226.21", "109.206.144.194", "109.248.57.198", "109.63.193.28", "109.67.149.36", "112.193.2.141", "114.224.30.147", "123.112.214.2", "123.185.66.220", "125.229.48.110", "130.0.220.119", "135.131.174.76", "141.135.6.172", "145.255.12.28", "159.2.80.240", "162.198.119.188", "163.58.65.191", "176.106.160.193", "178.141.159.36", "178.205.93.141", "183.166.227.12", "184.155.122.12", "185.219.109.179", "188.134.88.65", "188.241.36.166", "192.168.1.170", "195.14.48.110", "195.239.203.162", "202.131.84.11", "203.118.131.219", "203.129.18.0", "205.250.162.213", "212.15.59.91", "220.133.2.109", "24.35.254.197", "36.62.117.220", "38.15.38.26", "46.65.247.3", "47.253.32.11", "47.34.208.57", "49.231.43.170", "5.12.248.227", "62.0.93.190", "64.254.187.156", "67.172.84.54", "68.5.105.231", "68.6.175.76", "69.127.154.48", "69.197.174.72", "71.166.51.14", "71.183.186.77", "71.227.39.0", "72.80.216.47", "73.196.143.58", "73.204.157.123", "73.205.40.161", "73.51.157.106", "75.100.41.233", "76.232.65.235", "76.76.229.88", "78.107.240.148", "78.82.157.212", "80.235.212.62", "84.215.10.74", "84.215.4.105", "84.215.8.184", "84.244.36.203", "84.52.158.183", "86.30.69.50", "87.152.18.128", "88.69.241.119", "89.45.186.200", "92.221.123.123", "92.234.41.184", "94.27.192.108", "94.61.16.125", "95.105.142.58", "95.22.80.4", "95.52.90.167", "104.157.124.160", "109.198.29.98", "109.206.144.194", "109.67.149.36", "119.6.178.16", "143.177.124.174", "162.118.7.169", "162.198.119.188", "176.106.160.193", "184.146.2.29", "184.71.194.234", "188.97.174.241", "202.131.84.11", "203.118.131.219", "217.198.130.81", "220.133.2.109", "222.77.7.0", "37.78.112.47", "42.3.123.47", "46.189.185.59", "47.253.32.11", "47.34.208.57", "66.231.154.77", "69.197.174.72", "70.19.84.129", "71.227.39.0", "72.69.130.232", "73.51.157.106", "75.100.41.233", "75.172.49.125", "76.128.231.98", "76.76.229.88", "78.107.240.148", "78.180.96.7", "79.104.211.73", "82.37.10.82", "84.215.10.38", "84.215.4.105", "86.103.60.87", "87.118.169.200", "89.116.184.19", "89.242.3.102", "92.55.57.183", "93.43.225.93", "94.19.237.176", "94.253.36.50", "95.105.142.58", "95.22.80.4", "95.31.212.141", "97.90.194.187", "mmx-th-2.mmx.network"];

const list = ["1.10.230.84", "104.157.124.160", "107.137.68.128", "108.12.226.21", "109.198.29.98", "110.164.184.5", "113.250.145.115", "113.53.52.229", "119.6.178.16", "135.131.174.76", "141.135.6.172", "143.177.124.174", "156.47.99.16", "162.118.7.169", "162.198.119.188", "163.58.65.191", "174.166.225.36", "176.77.44.137", "178.141.191.38", "178.34.121.69", "183.166.206.176", "184.146.2.29", "184.71.194.234", "188.97.167.199", "195.239.203.162", "203.129.18.0", "212.15.59.91", "217.168.252.30", "217.198.130.81", "42.3.123.47", "46.142.230.108", "46.142.230.236", "46.189.185.59", "47.253.32.11", "47.34.208.57", "49.231.43.170", "66.231.154.77", "69.197.174.72", "70.187.229.11", "70.19.84.129", "71.227.39.0", "73.225.44.243", "75.172.49.125", "76.128.231.98", "76.232.65.235", "78.107.240.148", "78.180.96.7", "79.104.211.73", "80.235.212.62", "82.37.10.82", "82.76.87.170", "84.215.4.105", "84.90.4.150", "86.103.60.176", "86.103.61.3", "86.30.69.50", "87.118.169.200", "89.242.3.102", "93.43.225.93", "94.19.237.176", "94.253.34.120", "94.27.155.9", "95.105.142.58", "95.22.80.4", "95.31.212.141", "mmx-th-1.mmx.network", "mmx-th-2.mmx.network"];

var out = list.filter(peer => ref.includes(peer));

out = out.filter(peer => !peer.includes("mmx.network"));

const seed = ["69.197.174.72", "49.231.43.170", "110.164.184.5", "89.116.184.19"];

for(const peer of seed) {
    if(!out.includes(peer)) {
        out.push(peer);
    }
}

console.log(JSON.stringify(out, null, 4));