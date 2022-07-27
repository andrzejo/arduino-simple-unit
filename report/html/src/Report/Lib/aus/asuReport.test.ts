import * as api from '../../api';
import {transformReportToAsuReport} from "./asuReport";

jest.mock('../../api');

describe("ASU report transformer", () => {

    // @ts-ignore
    api.fetchTestCaseReport.mockResolvedValue({
        "testCase": "DisplayOledTest",
        "result": true,
        "success": 7,
        "failed": 0,
        "skipped": 0,
        "duration": 24,
        "tests": [
            {
                "name": "should_draw_glyph_splash",
                "success": true,
                "disabled": false,
                "assertions": 3,
                "failedAssertions": 0,
                "messages": [
                    "Saved screenshot to: file:///home/andrzej/Dev/my/moto-sensors/cmake-build-debug/test/ctest/resources/should_draw_glyph_splash-26.png "
                ],
                "artifacts": [
                    "/home/andrzej/Dev/my/moto-sensors/cmake-build-debug/test/ctest/resources/should_draw_glyph_splash-26.png"
                ],
                "failed": []
            },
            {
                "name": "should_draw_glyph2",
                "success": true,
                "disabled": false,
                "assertions": 2,
                "failedAssertions": 0,
                "messages": [
                    "Saved screenshot to: file:///home/andrzej/Dev/my/moto-sensors/cmake-build-debug/test/ctest/resources/should_draw_glyph2-39.png "
                ],
                "artifacts": [
                    "/home/andrzej/Dev/my/moto-sensors/cmake-build-debug/test/ctest/resources/should_draw_glyph2-39.png"
                ],
                "failed": []
            }
        ]
    });

    it("should transform report to ASU report", async () => {
        //given
        const report = getXml();

        //when
        const asuReport = await transformReportToAsuReport(report);

        //then
        expect(asuReport).toEqual({
            date: "2021-05-16 10:14:19",
            props: {
                "BuildName": "(empty)",
                "BuildStamp": "20210516-0641-Experimental",
                "Name": "(empty)"
            },
            tests: [
                {
                    "testCase": "DisplayOledTest",
                    "result": true,
                    "success": 7,
                    "failed": 0,
                    "skipped": 0,
                    "duration": 24,
                    "tests": [
                        {
                            "name": "should_draw_glyph_splash",
                            "success": true,
                            "disabled": false,
                            "assertions": 3,
                            "failedAssertions": 0,
                            "messages": [
                                "Saved screenshot to: file:///home/andrzej/Dev/my/moto-sensors/cmake-build-debug/test/ctest/resources/should_draw_glyph_splash-26.png "
                            ],
                            "artifacts": [
                                "/home/andrzej/Dev/my/moto-sensors/cmake-build-debug/test/ctest/resources/should_draw_glyph_splash-26.png"
                            ],
                            "failed": []
                        },
                        {
                            "name": "should_draw_glyph2",
                            "success": true,
                            "disabled": false,
                            "assertions": 2,
                            "failedAssertions": 0,
                            "messages": [
                                "Saved screenshot to: file:///home/andrzej/Dev/my/moto-sensors/cmake-build-debug/test/ctest/resources/should_draw_glyph2-39.png "
                            ],
                            "artifacts": [
                                "/home/andrzej/Dev/my/moto-sensors/cmake-build-debug/test/ctest/resources/should_draw_glyph2-39.png"
                            ],
                            "failed": []
                        }
                    ]
                }
            ]
        })
    })

    const getXml = () => {
        // language=xml
        return `<?xml version="1.0" encoding="UTF-8"?>
<testsuite timestamp="1621152859">
    <properties>
        <property name="BuildName" value="(empty)"/>
        <property name="BuildStamp" value="20210516-0641-Experimental"/>
        <property name="Name" value="(empty)"/>
    </properties>
    <testcase name="test_DisplayOled"
              classname="TestSuite"
              time="&#xA;&#x9;&#x9;&#x9;&#x9;&#x9;0.026082&#xA;&#x9;&#x9;&#x9;&#x9;">
        <system-out>[1/7] Running test DisplayOledTest::should_draw_glyph_splash... [OK]
            ---&gt; test message: Saved screenshot to:
            /execution/node/3/ws/build-ci/test/ctest/asu-resources/should_draw_glyph_splash-26.png
            [2/7] Running test DisplayOledTest::should_draw_glyph2... [OK]
            ---&gt; test message: Saved screenshot to:
            /execution/node/3/ws/build-ci/test/ctest/asu-resources/should_draw_glyph2-39.png
            [3/7] Running test DisplayOledTest::should_draw_status_glyphs... [OK]
            ---&gt; test message: Saved screenshot to:
            /execution/node/3/ws/build-ci/test/ctest/asu-resources/should_draw_status_glyphs-60.png
            [4/7] Running test DisplayOledTest::should_draw_status_glyphs_and_errors... [OK]
            ---&gt; test message: Saved screenshot to:
            /execution/node/3/ws/build-ci/test/ctest/asu-resources/should_draw_status_glyphs_and_errors-86.png
            [5/7] Running test DisplayOledTest::should_display_stop... [OK]
            ---&gt; test message: Saved screenshot to:
            /execution/node/3/ws/build-ci/test/ctest/asu-resources/should_display_stop-102.png
            [6/7] Running test DisplayOledTest::should_display_turn_left... [OK]
            ---&gt; test message: Saved screenshot to:
            /execution/node/3/ws/build-ci/test/ctest/asu-resources/should_display_turn_left-117.png
            [7/7] Running test DisplayOledTest::should_display_turn_right... [OK]
            ---&gt; test message: Saved screenshot to:
            /execution/node/3/ws/build-ci/test/ctest/asu-resources/should_display_turn_right-132.png
            Test case SUCCESSFUL. Stats: executed [7], success [7], failed [0], skipped: [0]. Assertions: total [18],
            failed [0].
        </system-out>
    </testcase>
    <system-out>
        BuildName: (empty)
        BuildStamp: 20210516-0641-Experimental
        Name: (empty)
    </system-out>
</testsuite>`
    }
})
