import * as React from "react";

import {AsuReport} from "../Lib/aus/asuReport";
import duration from "../Utils/duration";
import {build_timestamp, build_version} from "../../version";

import "./Header.scss"

type Props = {
    report: AsuReport
}

type ItemProps = {
    label: string,
    value: string,
    className?: string
}

const Item: React.FunctionComponent<ItemProps> = (props) => {
    return (
        <div className={"header-item " + (props.className || '')}>
            <div className={"header-label"}>
                {props.label}
            </div>
            <div className={"header-value"}>
                {props.value}
            </div>
        </div>
    )
}

const Header: React.FunctionComponent<Props> = (props) => {
    const {report} = props;

    const count = (prop: "success" | "failed" | "skipped" | "duration"): number => {
        return report.tests.reduce((acc, curr) => (acc + curr[prop]), 0);
    }

    const success = count("success");
    const failed = count("failed");
    const skipped = count("skipped");
    const dur = duration(count("duration"));
    const total = report.tests.reduce((acc, curr) => (acc + curr.tests.length), 0);
    const isSuccess = failed == 0;

    return (
        <div className={"header"}>
            <div className={"label"}>
                <div className={"name"}><img src={"icon.png"}/>Arduino Simple Unit report</div>
                <div className={"version"}>
                    version: {build_version()} <span>({build_timestamp()})</span>
                </div>
            </div>
            <div className={"status " + (isSuccess ? "success" : "failure")}>
                Status: {isSuccess ? "SUCCESS" : "FAILURE"}
            </div>
            <div className={"header-table"}>
                <Item label={"Timestamp (local time)"} value={report.date}/>
                <Item label={"Tests"} value={total.toString()} className={isSuccess ? "success" : ""}/>
                <Item label={"Duration"} value={dur}/>
                <Item label={"Success"} value={success.toString()}/>
                <Item label={"Skipped"} value={skipped.toString()}/>
                <Item label={"Failed"} value={failed.toString()} className={isSuccess ? "" : "failed"}/>
            </div>
        </div>
    )
};

export default Header