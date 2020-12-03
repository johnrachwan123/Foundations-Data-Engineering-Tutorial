#### 4

select '{" custkey ":' || c_custkey || ', " name ":"' || c_name
|| '", " nation ":{" nationkey ":' || n_nationkey || ', " name ":" ' || n_name || ' "}} ' as custjson
from customer , nation
where c_nationkey = n_nationkey limit 10;

